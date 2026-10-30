---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:07:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1793372591 48
1793372596 48
1793372601 46
1793372606 46
1793372611 46
1793372616 46
1793372621 46
1793372626 46
1793372631 45
1793372636 45
1793372641 45
1793372646 45
1793372651 45
1793372656 45
1793372661 45
1793372666 45
1793372671 45
1793372676 45
1793372681 45
1793372686 45
```
</details>

---

