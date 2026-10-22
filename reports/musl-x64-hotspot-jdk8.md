---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 12:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 76-94 cores)</summary>

```
1792686132 76
1792686137 76
1792686142 76
1792686147 76
1792686152 76
1792686157 94
1792686162 94
1792686167 94
1792686172 94
1792686177 94
1792686182 94
1792686187 94
1792686192 94
1792686197 94
1792686202 94
1792686207 94
1792686212 94
1792686217 94
1792686222 92
1792686227 92
```
</details>

---

