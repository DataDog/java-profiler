---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:32:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 61-70 cores)</summary>

```
1795192085 70
1795192090 70
1795192095 70
1795192100 70
1795192105 70
1795192110 61
1795192115 61
1795192120 61
1795192125 61
1795192130 61
1795192135 61
1795192140 61
1795192145 61
1795192150 61
1795192156 61
1795192161 61
1795192166 61
1795192171 61
1795192176 61
1795192181 61
```
</details>

---

