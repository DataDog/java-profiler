---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 06:42:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792492600 48
1792492605 48
1792492610 48
1792492615 48
1792492620 48
1792492625 48
1792492630 48
1792492635 43
1792492640 43
1792492645 43
1792492650 43
1792492655 43
1792492660 43
1792492665 43
1792492670 43
1792492675 43
1792492680 43
1792492685 43
1792492690 43
1792492695 48
```
</details>

---

