---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 16:04:35 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792785541 43
1792785546 43
1792785551 43
1792785556 43
1792785561 48
1792785566 48
1792785571 48
1792785576 48
1792785581 48
1792785586 48
1792785591 48
1792785596 48
1792785601 48
1792785606 48
1792785611 48
1792785616 48
1792785621 48
1792785626 48
1792785631 48
1792785636 48
```
</details>

---

