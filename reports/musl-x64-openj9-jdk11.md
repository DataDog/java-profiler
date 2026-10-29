---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 16:31:12 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1793305595 57
1793305600 57
1793305605 57
1793305610 57
1793305615 55
1793305620 55
1793305625 55
1793305630 55
1793305635 57
1793305641 57
1793305646 57
1793305651 57
1793305656 57
1793305661 57
1793305666 57
1793305671 57
1793305676 57
1793305681 57
1793305686 57
1793305691 57
```
</details>

---

