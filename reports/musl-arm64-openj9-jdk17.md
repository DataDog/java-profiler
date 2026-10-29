---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 09:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 8 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 12 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (3 unique values: 43-56 cores)</summary>

```
1793281824 43
1793281829 43
1793281834 43
1793281839 43
1793281844 56
1793281849 56
1793281854 45
1793281859 45
1793281864 45
1793281869 45
1793281874 45
1793281879 45
1793281884 45
1793281889 45
1793281894 45
1793281899 45
1793281904 45
1793281909 45
1793281914 45
1793281919 45
```
</details>

---

