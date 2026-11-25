---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:36:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 12 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 79-87 cores)</summary>

```
1795631555 79
1795631560 79
1795631565 79
1795631570 79
1795631575 79
1795631580 79
1795631585 79
1795631590 79
1795631595 79
1795631600 79
1795631605 79
1795631610 79
1795631615 79
1795631620 79
1795631625 79
1795631630 79
1795631635 79
1795631640 79
1795631645 79
1795631650 87
```
</details>

---

