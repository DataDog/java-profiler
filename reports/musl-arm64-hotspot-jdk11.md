---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:28:36 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 11 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1790094082 40
1790094087 40
1790094092 40
1790094097 40
1790094102 40
1790094107 40
1790094112 40
1790094117 40
1790094122 40
1790094127 40
1790094133 48
1790094138 48
1790094143 48
1790094148 48
1790094153 48
1790094158 48
1790094163 48
1790094168 48
1790094173 48
1790094178 48
```
</details>

---

