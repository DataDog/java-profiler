---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-10 15:42:04 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 12 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775849829 64
1775849834 64
1775849839 64
1775849844 64
1775849849 64
1775849854 64
1775849859 64
1775849864 64
1775849869 64
1775849874 64
1775849879 64
1775849884 64
1775849889 64
1775849894 64
1775849899 64
1775849904 64
1775849909 64
1775849914 64
1775849919 64
1775849924 64
```
</details>

---

