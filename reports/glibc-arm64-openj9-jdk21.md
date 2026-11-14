---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-14 06:23:03 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1794655157 26
1794655162 26
1794655167 26
1794655172 26
1794655177 26
1794655182 26
1794655187 26
1794655192 26
1794655197 26
1794655202 26
1794655207 26
1794655212 26
1794655217 26
1794655222 26
1794655227 21
1794655232 21
1794655237 21
1794655242 21
1794655247 21
1794655252 21
```
</details>

---

