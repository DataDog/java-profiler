---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:40:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (5 unique values: 20-27 cores)</summary>

```
1790238991 20
1790238996 20
1790239001 24
1790239006 24
1790239011 25
1790239016 25
1790239022 25
1790239027 25
1790239032 25
1790239037 25
1790239042 25
1790239047 25
1790239052 25
1790239057 25
1790239062 24
1790239067 24
1790239072 26
1790239077 26
1790239082 26
1790239087 26
```
</details>

---

