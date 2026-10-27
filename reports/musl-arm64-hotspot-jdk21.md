---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:43:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 50-60 cores)</summary>

```
1793101154 54
1793101159 54
1793101164 54
1793101169 54
1793101174 54
1793101179 54
1793101184 54
1793101189 54
1793101194 54
1793101199 54
1793101204 54
1793101209 54
1793101214 54
1793101219 54
1793101224 54
1793101229 54
1793101234 54
1793101239 54
1793101244 50
1793101249 50
```
</details>

---

