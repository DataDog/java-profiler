---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:32:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 11 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793287646 48
1793287651 48
1793287656 48
1793287661 48
1793287666 48
1793287671 48
1793287676 48
1793287681 48
1793287686 48
1793287691 48
1793287696 48
1793287701 48
1793287706 48
1793287711 48
1793287716 48
1793287721 48
1793287726 48
1793287731 48
1793287736 48
1793287741 48
```
</details>

---

