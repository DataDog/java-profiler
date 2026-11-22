---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 17:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 31-66 cores)</summary>

```
1795386105 57
1795386110 57
1795386115 57
1795386120 57
1795386125 57
1795386130 57
1795386135 66
1795386140 66
1795386145 57
1795386150 57
1795386155 57
1795386160 57
1795386165 57
1795386170 57
1795386175 57
1795386180 57
1795386185 57
1795386190 57
1795386195 57
1795386200 57
```
</details>

---

