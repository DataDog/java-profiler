---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:30:39 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793615102 48
1793615107 48
1793615112 48
1793615117 48
1793615122 48
1793615127 48
1793615132 48
1793615137 48
1793615142 48
1793615147 48
1793615152 48
1793615157 48
1793615162 48
1793615167 48
1793615172 48
1793615177 48
1793615182 48
1793615187 48
1793615192 48
1793615197 48
```
</details>

---

