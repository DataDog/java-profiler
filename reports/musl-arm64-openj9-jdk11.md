---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:23:35 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 49-64 cores)</summary>

```
1795195148 49
1795195153 49
1795195158 49
1795195163 49
1795195168 49
1795195173 59
1795195178 59
1795195183 59
1795195188 59
1795195193 59
1795195198 59
1795195203 59
1795195208 59
1795195213 59
1795195218 59
1795195223 59
1795195228 64
1795195233 64
1795195238 59
1795195243 59
```
</details>

---

