---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:53:27 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793288677 48
1793288682 48
1793288687 48
1793288692 48
1793288697 48
1793288702 48
1793288707 48
1793288712 48
1793288717 48
1793288722 48
1793288727 48
1793288732 48
1793288737 48
1793288742 48
1793288747 48
1793288752 48
1793288757 48
1793288762 48
1793288767 48
1793288772 48
```
</details>

---

