---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 15:28:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1787080923 14
1787080928 14
1787080933 14
1787080938 14
1787080943 14
1787080948 14
1787080953 14
1787080958 14
1787080963 14
1787080968 14
1787080973 14
1787080978 14
1787080983 14
1787080988 14
1787080993 14
1787080998 14
1787081003 14
1787081008 14
1787081013 14
1787081018 34
```
</details>

---

