---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:33:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 11 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789680188 25
1789680193 25
1789680198 25
1789680203 30
1789680208 30
1789680213 30
1789680218 30
1789680223 30
1789680228 30
1789680233 30
1789680238 30
1789680243 30
1789680248 30
1789680253 30
1789680258 30
1789680263 30
1789680268 30
1789680273 30
1789680278 30
1789680283 30
```
</details>

---

