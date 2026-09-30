---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:24:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 67-69 cores)</summary>

```
1790770757 67
1790770762 67
1790770767 69
1790770772 69
1790770777 69
1790770782 69
1790770787 69
1790770792 69
1790770797 67
1790770802 67
1790770807 67
1790770812 67
1790770817 67
1790770822 67
1790770827 69
1790770832 69
1790770837 69
1790770842 69
1790770847 69
1790770852 69
```
</details>

---

