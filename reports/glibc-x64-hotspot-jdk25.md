---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 13:40:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 20.00/sec |
| Health Score | 1250% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 25.23/sec |
| Health Score | 1577% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1769538867 30
1769538872 30
1769538877 30
1769538882 30
1769538887 30
1769538892 30
1769538897 30
1769538902 30
1769538907 30
1769538912 30
1769538917 30
1769538922 32
1769538927 32
1769538932 32
1769538937 32
1769538942 32
1769538947 32
1769538952 32
1769538957 32
1769538962 32
```
</details>

---

