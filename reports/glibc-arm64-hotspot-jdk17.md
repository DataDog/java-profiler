---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 10:29:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 42-54 cores)</summary>

```
1792679035 51
1792679040 51
1792679045 54
1792679050 54
1792679055 54
1792679060 54
1792679065 54
1792679070 54
1792679075 54
1792679080 54
1792679085 54
1792679090 54
1792679095 42
1792679100 42
1792679105 42
1792679110 42
1792679115 42
1792679120 42
1792679125 42
1792679130 42
```
</details>

---

