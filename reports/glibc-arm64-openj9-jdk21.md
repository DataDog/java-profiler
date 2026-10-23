---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 16:40:58 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1792787797 40
1792787802 40
1792787807 40
1792787812 40
1792787817 40
1792787822 40
1792787827 40
1792787832 40
1792787837 40
1792787842 40
1792787847 40
1792787852 40
1792787857 40
1792787862 40
1792787867 40
1792787872 40
1792787877 40
1792787882 40
1792787887 40
1792787892 40
```
</details>

---

