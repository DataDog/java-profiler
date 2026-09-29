---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 11:52:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 70-80 cores)</summary>

```
1790696782 80
1790696787 80
1790696792 80
1790696797 70
1790696802 70
1790696807 70
1790696812 70
1790696817 70
1790696822 70
1790696827 70
1790696832 70
1790696837 70
1790696842 70
1790696847 70
1790696852 70
1790696857 70
1790696862 70
1790696867 70
1790696872 70
1790696877 70
```
</details>

---

