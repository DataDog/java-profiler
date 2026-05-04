---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:22:24 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857133 64
1777857138 64
1777857143 64
1777857148 64
1777857153 64
1777857158 64
1777857163 64
1777857168 64
1777857173 64
1777857178 64
1777857183 64
1777857188 64
1777857193 64
1777857198 64
1777857203 64
1777857208 64
1777857213 64
1777857218 64
1777857223 64
1777857228 64
```
</details>

---

