---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 07:06:38 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 10 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795521757 33
1795521762 33
1795521767 64
1795521772 64
1795521777 64
1795521782 64
1795521787 64
1795521792 64
1795521797 64
1795521802 64
1795521807 64
1795521812 64
1795521817 64
1795521822 64
1795521827 64
1795521832 64
1795521837 64
1795521842 64
1795521847 64
1795521852 64
```
</details>

---

