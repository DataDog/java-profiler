---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 08:24:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1790770772 71
1790770777 71
1790770782 73
1790770787 73
1790770792 73
1790770797 73
1790770802 73
1790770807 73
1790770812 73
1790770817 73
1790770822 73
1790770827 73
1790770833 73
1790770838 73
1790770843 73
1790770848 73
1790770853 73
1790770858 73
1790770863 73
1790770868 73
```
</details>

---

