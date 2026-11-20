---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:23:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 40-54 cores)</summary>

```
1795195133 46
1795195138 46
1795195143 46
1795195148 40
1795195153 40
1795195158 40
1795195163 40
1795195168 40
1795195173 40
1795195178 40
1795195183 40
1795195188 40
1795195193 40
1795195198 40
1795195203 40
1795195208 40
1795195213 40
1795195218 40
1795195223 40
1795195228 54
```
</details>

---

