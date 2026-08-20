---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 08:51:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 76-94 cores)</summary>

```
1787229949 76
1787229954 76
1787229959 76
1787229964 76
1787229969 76
1787229974 94
1787229979 94
1787229984 94
1787229989 94
1787229994 94
1787229999 94
1787230004 94
1787230009 94
1787230014 94
1787230019 94
1787230024 94
1787230029 94
1787230034 94
1787230039 94
1787230044 94
```
</details>

---

