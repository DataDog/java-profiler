---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 05:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 9 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 925 |
| Sample Rate | 15.42/sec |
| Health Score | 964% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792662619 43
1792662624 48
1792662629 48
1792662634 48
1792662639 48
1792662644 48
1792662649 48
1792662654 48
1792662659 48
1792662664 48
1792662669 48
1792662674 48
1792662679 48
1792662684 48
1792662689 48
1792662694 48
1792662699 48
1792662704 48
1792662709 48
1792662714 48
```
</details>

---

