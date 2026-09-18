---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:33:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789720073 30
1789720078 30
1789720083 30
1789720088 30
1789720093 30
1789720098 30
1789720103 30
1789720108 30
1789720113 30
1789720118 30
1789720123 30
1789720128 30
1789720133 30
1789720138 30
1789720143 30
1789720148 30
1789720154 30
1789720159 30
1789720164 30
1789720169 30
```
</details>

---

