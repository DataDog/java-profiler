---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-23 00:55:50 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 13 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787460702 48
1787460707 43
1787460712 43
1787460717 43
1787460722 43
1787460727 43
1787460732 43
1787460737 43
1787460742 43
1787460747 43
1787460752 43
1787460757 43
1787460762 43
1787460767 43
1787460772 43
1787460777 43
1787460782 43
1787460787 43
1787460792 43
1787460797 43
```
</details>

---

