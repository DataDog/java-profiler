---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-01 20:28:10 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1793582673 16
1793582678 16
1793582683 16
1793582688 16
1793582693 16
1793582698 16
1793582703 16
1793582708 16
1793582713 16
1793582718 16
1793582723 16
1793582728 16
1793582733 16
1793582738 16
1793582743 16
1793582748 16
1793582753 16
1793582758 16
1793582763 16
1793582768 16
```
</details>

---

