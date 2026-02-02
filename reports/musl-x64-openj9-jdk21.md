---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-02 09:31:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 13 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (8 unique values: 39-59 cores)</summary>

```
1770042103 39
1770042108 44
1770042113 44
1770042118 44
1770042123 49
1770042128 49
1770042133 59
1770042138 59
1770042143 59
1770042148 59
1770042153 59
1770042158 52
1770042163 52
1770042168 52
1770042173 52
1770042178 52
1770042183 52
1770042188 52
1770042193 52
1770042198 52
```
</details>

---

