---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 07:48:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1787312667 46
1787312672 48
1787312677 48
1787312682 48
1787312687 48
1787312692 48
1787312697 48
1787312702 43
1787312707 43
1787312712 43
1787312717 43
1787312722 43
1787312727 43
1787312732 43
1787312737 43
1787312742 38
1787312747 38
1787312752 38
1787312757 38
1787312762 38
```
</details>

---

