---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 12:40:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 31-54 cores)</summary>

```
1792686856 31
1792686861 31
1792686866 31
1792686871 31
1792686876 31
1792686881 44
1792686886 44
1792686891 54
1792686896 54
1792686901 54
1792686906 54
1792686911 54
1792686916 54
1792686921 54
1792686926 54
1792686931 54
1792686936 54
1792686941 54
1792686946 54
1792686951 54
```
</details>

---

