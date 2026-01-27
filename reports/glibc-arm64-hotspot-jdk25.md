---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-01-27 13:40:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 19.67/sec |
| Health Score | 1229% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 17 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769538892 24
1769538897 24
1769538902 24
1769538907 24
1769538912 24
1769538917 24
1769538922 24
1769538927 24
1769538932 24
1769538937 24
1769538942 24
1769538947 24
1769538952 24
1769538957 24
1769538962 24
1769538967 24
1769538972 24
1769538977 24
1769538982 24
1769538987 24
```
</details>

---

