---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:47:04 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 15 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1789731786 30
1789731791 30
1789731796 30
1789731801 30
1789731806 30
1789731811 30
1789731816 30
1789731821 30
1789731826 30
1789731831 30
1789731836 30
1789731841 30
1789731846 30
1789731851 30
1789731856 30
1789731861 30
1789731866 30
1789731871 30
1789731876 30
1789731881 30
```
</details>

---

