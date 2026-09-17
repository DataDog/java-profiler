---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-17 17:33:14 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 72-81 cores)</summary>

```
1789680186 72
1789680191 72
1789680196 72
1789680202 72
1789680207 81
1789680212 81
1789680217 81
1789680222 81
1789680227 81
1789680232 81
1789680237 81
1789680242 81
1789680247 81
1789680252 81
1789680257 81
1789680262 81
1789680267 81
1789680272 81
1789680277 81
1789680282 79
```
</details>

---

