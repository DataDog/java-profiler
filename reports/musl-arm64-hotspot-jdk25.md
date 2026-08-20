---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 05:42:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 14 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (3 unique values: 62-64 cores)</summary>

```
1787218670 62
1787218675 62
1787218680 62
1787218685 62
1787218690 62
1787218695 62
1787218700 62
1787218705 62
1787218710 62
1787218715 62
1787218720 63
1787218725 63
1787218730 63
1787218735 63
1787218740 63
1787218745 63
1787218750 63
1787218755 63
1787218760 63
1787218765 63
```
</details>

---

