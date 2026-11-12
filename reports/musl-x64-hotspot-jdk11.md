---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:55:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 72-93 cores)</summary>

```
1794484147 72
1794484152 72
1794484157 72
1794484162 72
1794484167 72
1794484172 72
1794484177 72
1794484182 72
1794484187 72
1794484192 72
1794484197 72
1794484202 72
1794484207 93
1794484212 93
1794484217 93
1794484222 93
1794484227 93
1794484232 93
1794484237 93
1794484242 93
```
</details>

---

