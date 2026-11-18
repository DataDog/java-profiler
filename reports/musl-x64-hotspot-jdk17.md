---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 00:06:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 26-96 cores)</summary>

```
1794978119 26
1794978124 26
1794978129 54
1794978134 54
1794978139 54
1794978144 54
1794978149 63
1794978154 63
1794978159 63
1794978164 63
1794978169 63
1794978174 63
1794978179 63
1794978184 63
1794978189 63
1794978194 63
1794978199 63
1794978204 63
1794978209 96
1794978214 96
```
</details>

---

