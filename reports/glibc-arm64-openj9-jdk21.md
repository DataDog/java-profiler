---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 12:28:38 EDT

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
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1792772682 14
1792772687 14
1792772692 34
1792772697 34
1792772702 34
1792772707 34
1792772712 34
1792772717 34
1792772722 34
1792772727 34
1792772732 34
1792772737 34
1792772742 34
1792772747 34
1792772752 34
1792772757 34
1792772762 34
1792772767 34
1792772772 34
1792772777 34
```
</details>

---

