---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 15:13:42 EST

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
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793995757 48
1793995762 48
1793995767 48
1793995772 48
1793995777 48
1793995782 48
1793995787 48
1793995792 48
1793995797 48
1793995802 48
1793995807 48
1793995812 48
1793995817 48
1793995822 48
1793995827 48
1793995832 48
1793995837 48
1793995842 48
1793995847 48
1793995852 48
```
</details>

---

