---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 09:20:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 57-60 cores)</summary>

```
1778591666 60
1778591672 60
1778591677 60
1778591682 60
1778591687 60
1778591692 60
1778591697 60
1778591702 60
1778591707 57
1778591712 57
1778591717 57
1778591722 57
1778591727 57
1778591732 57
1778591737 57
1778591742 57
1778591747 57
1778591752 57
1778591757 57
1778591762 57
```
</details>

---

