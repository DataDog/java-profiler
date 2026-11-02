---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:30:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 13 |
| Allocations | 182 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1793615079 40
1793615084 40
1793615089 40
1793615094 40
1793615099 40
1793615104 40
1793615109 40
1793615114 40
1793615119 40
1793615124 40
1793615129 40
1793615134 40
1793615139 40
1793615144 40
1793615149 40
1793615154 40
1793615159 40
1793615164 40
1793615169 40
1793615174 35
```
</details>

---

