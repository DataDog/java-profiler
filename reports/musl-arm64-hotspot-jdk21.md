---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 06:45:42 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790592091 48
1790592096 48
1790592101 48
1790592106 48
1790592111 48
1790592116 43
1790592121 43
1790592126 43
1790592131 43
1790592136 43
1790592141 43
1790592146 43
1790592151 43
1790592156 43
1790592161 43
1790592166 43
1790592171 43
1790592176 43
1790592181 43
1790592186 43
```
</details>

---

