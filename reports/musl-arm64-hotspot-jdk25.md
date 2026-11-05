---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 09:37:19 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 13 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793889118 43
1793889123 43
1793889128 43
1793889133 43
1793889138 43
1793889143 48
1793889148 48
1793889153 48
1793889158 48
1793889163 48
1793889168 48
1793889173 48
1793889178 48
1793889183 48
1793889188 48
1793889193 48
1793889198 48
1793889203 48
1793889208 48
1793889213 48
```
</details>

---

