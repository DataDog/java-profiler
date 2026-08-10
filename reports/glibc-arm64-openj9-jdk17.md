---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 08:31:26 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1786364697 32
1786364702 32
1786364707 32
1786364712 32
1786364717 32
1786364722 32
1786364727 32
1786364732 32
1786364737 32
1786364742 32
1786364747 32
1786364752 32
1786364757 32
1786364762 32
1786364767 32
1786364772 32
1786364777 24
1786364782 24
1786364787 22
1786364792 22
```
</details>

---

