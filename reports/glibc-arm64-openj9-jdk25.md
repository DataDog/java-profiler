---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 15:13:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1793995772 28
1793995777 28
1793995782 28
1793995787 28
1793995792 28
1793995797 28
1793995802 28
1793995807 28
1793995812 28
1793995817 28
1793995822 28
1793995827 28
1793995832 28
1793995837 28
1793995842 28
1793995847 28
1793995852 28
1793995857 28
1793995862 28
1793995867 28
```
</details>

---

