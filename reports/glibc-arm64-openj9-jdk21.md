---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-31 06:53:47 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 14 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1793443797 48
1793443802 48
1793443807 43
1793443812 43
1793443817 43
1793443822 43
1793443827 43
1793443832 43
1793443837 43
1793443842 43
1793443847 41
1793443852 41
1793443857 41
1793443862 41
1793443867 41
1793443872 41
1793443877 41
1793443882 41
1793443887 43
1793443892 43
```
</details>

---

