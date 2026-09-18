---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 08:40:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (5 unique values: 41-47 cores)</summary>

```
1789734937 46
1789734942 41
1789734947 41
1789734952 41
1789734957 41
1789734962 41
1789734967 41
1789734972 41
1789734977 41
1789734982 41
1789734987 41
1789734992 41
1789734997 41
1789735002 41
1789735007 41
1789735012 43
1789735017 43
1789735022 43
1789735027 47
1789735032 47
```
</details>

---

