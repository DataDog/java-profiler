---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-17 17:33:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1789680188 33
1789680193 33
1789680198 33
1789680203 33
1789680208 33
1789680213 33
1789680218 33
1789680223 33
1789680228 33
1789680233 33
1789680238 33
1789680243 33
1789680248 33
1789680253 33
1789680258 33
1789680263 64
1789680268 64
1789680273 64
1789680278 64
1789680283 64
```
</details>

---

