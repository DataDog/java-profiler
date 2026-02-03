---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 09:53:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 896 |
| Sample Rate | 14.93/sec |
| Health Score | 933% |
| Threads | 13 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1770130078 38
1770130083 38
1770130088 38
1770130093 38
1770130098 43
1770130103 43
1770130108 43
1770130113 43
1770130118 43
1770130123 43
1770130128 43
1770130133 43
1770130138 43
1770130143 43
1770130148 43
1770130153 43
1770130158 43
1770130163 43
1770130168 43
1770130173 43
```
</details>

---

