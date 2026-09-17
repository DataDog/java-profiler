---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:03:57 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1789682145 40
1789682150 40
1789682155 40
1789682161 40
1789682166 40
1789682171 40
1789682176 40
1789682181 40
1789682186 40
1789682191 40
1789682196 48
1789682201 48
1789682206 48
1789682211 48
1789682216 48
1789682221 48
1789682226 48
1789682231 48
1789682236 48
1789682241 48
```
</details>

---

