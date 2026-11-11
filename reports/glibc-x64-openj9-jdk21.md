---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 13:18:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 86-91 cores)</summary>

```
1794420821 88
1794420826 88
1794420831 86
1794420836 86
1794420841 86
1794420846 86
1794420851 86
1794420856 86
1794420861 86
1794420866 86
1794420871 86
1794420876 86
1794420881 86
1794420886 86
1794420891 86
1794420896 86
1794420901 86
1794420906 86
1794420911 91
1794420916 91
```
</details>

---

