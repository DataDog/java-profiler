---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 11:02:22 EST

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
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793635102 48
1793635107 48
1793635113 48
1793635118 48
1793635123 48
1793635128 48
1793635133 48
1793635138 48
1793635143 48
1793635148 48
1793635153 48
1793635158 48
1793635163 48
1793635168 48
1793635173 48
1793635178 48
1793635183 48
1793635188 48
1793635193 48
1793635198 48
```
</details>

---

